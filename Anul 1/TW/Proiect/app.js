const createError = require('http-errors');
const express = require('express');
const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');
const db_rez = require('./db_rezultate.js');
const pdf_rez = require('./pdf_rezultate.js');

const app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.get('/get_bilet', async function(req, res) {
    const pacient = await db_rez.GetPacient(req.query.cnp);
    if(pacient.length == 0)
    {
        res.status(404);      
        res.send('Pacientul nu a fost gasit.');
        return;
    }
    const bilet = await db_rez.GetBilet(req.query.cnp, req.query.id);
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
    const grupe = await db_rez.GetGrupe(Array.from(codgs));

    const pdf = await pdf_rez.GetPdf(pacient[0], bilet[0], grupe);
    res.contentType("application/pdf");
    res.setHeader("Content-disposition", "filename=rezultat.pdf");
    res.send(pdf);
    return;
})

module.exports = app;