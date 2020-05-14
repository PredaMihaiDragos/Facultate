const createError = require('http-errors');
const express = require('express');
const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');
const db = require('./db.js');
const pdf_rez = require('./pdf_rezultate.js');

const app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.put("/chestionar", async function(req, res) {
    const cnp = req.body.cnp;
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

    await db.AddProgramare(nume, telefon, email, mesaj);
    res.status(201);
    res.send("Succes");
})

app.get('/get_bilet', async function(req, res) {
    const pacient = await db.GetPacient(req.query.cnp);
    if(pacient.length == 0)
    {
        res.status(404);      
        res.send('Pacientul nu a fost gasit.');
        return;
    }
    const bilet = await db.GetBilet(req.query.cnp, req.query.id);
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

module.exports = app;