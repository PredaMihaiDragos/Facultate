const createError = require('http-errors');
const express = require('express');
const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');

const app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

class lbilet
{
    constructor()
    {   
       this.aDen = "testaden";
       this.aVmin = "testvmin";
       this.aVmax = "testvmax";
       this.aRez = "testrez";
       this.aUma = "testuma";
       this.aCoda = "testcoda";
       this.aCodg = "testcodg";

       this.sDen = ["sden1", "sden2"];
       this.sVmin = ["sVmin1", "sVmin2"];
       this.sVmax = ["svmax1", "svmax2"];
       this.sRez = ["srez1", "srez2"];
       this.sUma = ["suma1", "suma2"];
    }
}

test = [new lbilet(), new lbilet()];

console.log(JSON.stringify(test));

module.exports = app;