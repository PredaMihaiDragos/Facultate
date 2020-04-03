const mysql = require('mysql');

let con = mysql.createConnection({
    host: "192.168.0.192",
    user: "root",
    password: "",
    database: "test"
})

function Query(query, successCallback, errorCallback) {
    con.query(query, function(err, result, fields){
        if (err) {
            return errorCallback(err);
        }
        return successCallback(result);
    }); 
}

function GetPacient(cnp) {
    cnp = mysql.escape(cnp);
    let query = "SELECT CNP, Name FROM pacient WHERE CNP=" + cnp;
    return new Promise((resolve, reject) => {
        Query(query,(successResponse) => {
            resolve(successResponse);
        }, (errorResponse) => {
            reject(errorResponse)
        });
    });
}

function GetBilet(cnp, id) {
    cnp = mysql.escape(cnp);
    id = mysql.escape(id);
    let query = "SELECT * FROM bilet WHERE CUVCODV=" + id + " AND IDP=" + cnp;
    return new Promise((resolve, reject) => {
        Query(query,(successResponse) => {
            resolve(successResponse);
        }, (errorResponse) => {
            reject(errorResponse)
        });
    });
}

function GetGrupe(codgs) {
    let query = "SELECT CODG, NUME FROM grupa WHERE CODG IN (";
    for(let i = 0; i < codgs.length; i++)
    {
        codgs[i] = mysql.escape(codgs[i]);
        query += codgs[i];
        if(i != codgs.length - 1)
            query += ",";
    }
    query += ") ORDER BY CODG";
    return new Promise((resolve, reject) => {
        Query(query,(successResponse) => {
            resolve(successResponse);
        }, (errorResponse) => {
            reject(errorResponse)
        });
    });
}

module.exports.GetPacient = GetPacient;
module.exports.GetBilet = GetBilet;
module.exports.GetGrupe = GetGrupe;