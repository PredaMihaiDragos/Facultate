const mysql = require('mysql');

let con = mysql.createConnection({
    host: "192.168.0.192",
    user: "root",
    password: "",
    database: "test"
})

function GetPacient(query, successCallback, errorCallback) {
    con.query(query, function(err, result, fields){
        if (err) {
            return errorCallback(err);
        }
        return successCallback(result);
    }); 
}

function GetPacientWrapper(cnp) {
    let query = "SELECT CNP, Name FROM pacient WHERE CNP = '" + cnp + "'";
    return new Promise((resolve, reject) => {
        GetPacient(query,(successResponse) => {
            resolve(successResponse);
        }, (errorResponse) => {
            reject(errorResponse)
        });
    });
}

module.exports.GetPacient = GetPacientWrapper;