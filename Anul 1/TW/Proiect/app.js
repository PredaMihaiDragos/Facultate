const createError = require('http-errors');
const express = require('express');
const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');
const db = require('./db.js');
const pdf_rez = require('./pdf_rezultate.js');
const regex = require('./regex.js');
const log = require('./log.js');

const app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.put("/chestionar", async function(req, res) {
    try
    {
        const cnp = String(req.body.cnp);
        const parere = req.body.parere;
        const calitate = req.body.calitate;
        const pret = req.body.pret;
        const promptitudine = req.body.promptitudine;
        const timp = req.body.timp;

        if(!regex.cnp.test(cnp))
        {
            res.status(400);
            res.send("CNP-ul introdus este invalid!");
            return;
        }
        const pacient = await db.GetPacient(cnp);
        if(pacient.length == 0)
        {
            res.status(404);
            res.send("Nu am gasit niciun pacient cu CNP-ul dat.");
            return;
        }
        db.AddEvent("chestionar_timp", timp);
        await db.AddReview(cnp, parere, calitate, pret, promptitudine, pacient);
        res.status(201);
        var datetime = new Date();
        log.write(`[${datetime}] IP-ul ${req.ip} a modificat raspunsul la chestionar cu cnp-ul ${cnp}.\n`);
        res.send("Succes");
    }
    catch(err)
    {
        res.status(500);
        res.send("Internal error: " + err);
    }
})

app.delete("/delete_chestionar", async function(req, res) {
    try
    {
        const cnp = req.body.cnp;
        if(!regex.cnp.test(cnp))
        {
            res.status(400);
            res.send("CNP-ul introdus este invalid!");
            return;
        }
        const pacient = await db.GetPacient(cnp);
        if(pacient.length == 0)
        {
            res.status(403);
            res.send("Nu am gasit niciun pacient cu CNP-ul dat.");
            return;
        }
        await db.DeleteReview(cnp);
        res.status(201);
        var datetime = new Date();
        log.write(`[${datetime}] IP-ul ${req.ip} a sters raspunsul la chestionar cu cnp-ul ${cnp}.\n`);
        res.send("Succes");
    }
    catch(err)
    {
        res.status(500);
        res.send("Internal error: " + err);
    }
})

app.post("/programari", async function(req, res) {
    try
    {
        const nume = req.body.nume;
        const telefon = req.body.telefon;
        const email = req.body.email;
        const mesaj = req.body.mesaj;

        if(!regex.name.test(nume))
        {
            res.status(400);
            res.send("Numele introdus este invalid!");
            return;
        }
        if(!regex.phone.test(telefon))
        {
            res.status(400);
            res.send("Telefonul introdus este invalid!");
            return;
        }
        if(!regex.mail.test(email))
        {
            res.status(400);
            res.send("Mailul introdus este invalid!");
            return;
        }

        await db.AddProgramare(nume, telefon, email, mesaj);
        res.status(201);
        var datetime = new Date();
        log.write(`[${datetime}] IP-ul ${req.ip} a adaugat o programare cu numele ${nume}.\n`);
        res.send("Succes");
    }
    catch(err)
    {
        res.status(500);
        res.send("Internal error: " + err);
    }
})

app.get('/get_bilet', async function(req, res) {
    try
    {
        const cnp = req.query.cnp;
        const id = req.query.id;
        if(!regex.cnp.test(cnp))
        {
            res.status(400);
            res.send("CNP-ul introdus este invalid!");
            return;
        }
        if(!regex.bilet.test(id))
        {
            res.status(400);
            res.send("ID-ul introdus este invalid!");
            return;
        }
        const pacient = await db.GetPacient(cnp);
        if(pacient.length == 0)
        {
            res.status(404);      
            res.send('Pacientul nu a fost gasit.');
            return;
        }
        const bilet = await db.GetBilet(cnp, id);
        if(bilet.length == 0)
        {
            res.status(404);      
            res.send('Biletul nu a fost gasit.');
            return;
        }
        bilet[0].ANALIZE = JSON.parse(bilet[0].ANALIZE);
        const analize = bilet[0].ANALIZE;
        codgs = new Set();
        for(let i = 0; i < analize.length; i++)
            codgs.add(analize[i].aCodg);

        db.AddEvent("rezultate_primit");
        const grupe = await db.GetGrupe(Array.from(codgs));
        const pdf = await pdf_rez.GetPdf(pacient[0], bilet[0], grupe);
        res.contentType("application/pdf");
        res.setHeader("Content-disposition", "filename=rezultat.pdf");
        var datetime = new Date();
        log.write(`[${datetime}] IP-ul ${req.ip} a vizualizat biletul ${id}.\n`);
        res.send(pdf);
    }
    catch(err)
    {
        res.status(500);
        res.send("Internal error: " + err);
    }
})

app.post("/chestionarClick", async function(req, res) {
    try
    {
        await db.AddEvent("chestionar_click");
        res.status(201);
        res.send("Succes");
    }
    catch(err)
    {
        res.status(500);
        res.send("Internal error: " + err);
    }
})

app.post("/sectionView", async function(req, res) {
    try
    {
        await db.AddEvent(req.body.section + "_view");
        res.status(201);
        res.send("Succes");
    }
    catch(err)
    {
        res.status(500);
        res.send("Internal error: " + err);
    }
})

module.exports = app;