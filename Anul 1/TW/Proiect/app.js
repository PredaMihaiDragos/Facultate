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

       this.sRez = ["srez1", "srez2"];
       this.sUma = ["suma1", "suma2"];
app.get('/get_pacient', async function(req, res) {
    const x = await db_rez.GetPacient("101003");
    res.send(x);
})

module.exports = app;