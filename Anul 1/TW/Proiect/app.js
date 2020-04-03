const createError = require('http-errors');
const express = require('express');
const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');
const db_rez = require('./db_rezultate.js');

const app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.get('/get_pacient', async function(req, res) {
    const x = await db_rez.GetPacient(req.query.cnp);

    if(x.length > 0)
        res.send(x[0]);
    else
    {
        res.status(404);      
        res.send('Pacientul nu a fost gasit.');
    }
})

app.get('/get_bilet', async function(req, res) {
    const x = await db_rez.GetBilet(req.query.cnp, req.query.id);
    if(x.length > 0)
        res.send(x[0]);
    else
    {
        res.status(404);      
        res.send('Biletul nu a fost gasit.');
    }
})

module.exports = app;