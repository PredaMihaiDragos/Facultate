const createError = require('http-errors');
const express = require('express');
const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');
const db = require('./db.js');
const pdf_rez = require('./pdf_rezultate.js');
const regex = require('./regex.js');

const app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.put("/chestionar", async function(req, res) {
    const cnp = String(req.body.cnp);
    if(!regex.cnp.test(cnp))
    {
        res.status(400);
        res.send("CNP-ul introdus este invalid!");
        return;
    }
    const parere = req.body.parere;
    const calitate = req.body.calitate;
    const pret = req.body.pret;
    const promptitudine = req.body.promptitudine;
    const pacient = await db.GetPacient(cnp);
    if(pacient.length == 0)
    {
        res.status(404);
        res.send("Nu am gasit niciun pacient cu CNP-ul dat.");
        return;
    }
    await db.AddReview(cnp, parere, calitate, pret, promptitudine, pacient);
    res.status(201);
    res.send("Succes");
})

app.delete("/delete_chestionar", async function(req, res) {
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
    res.send("Succes");
})

app.post("/programari", async function(req, res) {
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
    res.send("Succes");
})

app.get('/get_bilet', async function(req, res) {
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
    const grupe = await db.GetGrupe(Array.from(codgs));

    const pdf = await pdf_rez.GetPdf(pacient[0], bilet[0], grupe);
    res.contentType("application/pdf");
    res.setHeader("Content-disposition", "filename=rezultat.pdf");
    res.send(pdf);
    return;
})

app.post("/chestionarClick", async function(req, res) {
    res.status(201);
    res.send("Succes");
})

app.post("/sectionView", async function(req, res) {
    res.status(201);
    res.send("Succes");
})

module.exports = app;