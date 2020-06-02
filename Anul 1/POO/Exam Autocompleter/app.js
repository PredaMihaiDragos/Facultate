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

let allUpdates = [];

function removeSpaces(str)
{
    return str.replace(/\s/g, '');
}


function AddUpdate(value)
{
    allUpdates.push(value);
}

function GetMatches(value)
{
    return allUpdates.filter(upd => (removeSpaces(upd).startsWith(removeSpaces(value)) && removeSpaces(upd) != removeSpaces(value)));
}

app.post("/update", async function(req, res) {
    try
    {
        AddUpdate(req.body.json);
        res.status(200);
        res.send("Succes");
    }
    catch(err)
    {
        res.status(500);
        res.send("Internal error: " + err);
    }
})

app.post("/get", async function(req, res) {
    try
    {
        const matches = GetMatches(req.body.json);
        let ret = "";
        for(let i = 0; i < matches.length; i++)
            ret += matches[i] + "\n/*--------------------FINISH--------------------*/\n\n";
        res.status(200);
        res.send(ret);
    }
    catch(err)
    {
        res.status(500);
        res.send("Internal error: " + err);
    }
})

module.exports = app;