class pacient
{
    constructor(obj)
    {
        this.name = obj['Name'];
        this.cnp = obj['CNP'];
        let an_nastere = -1, luna_nastere = -1, zi_nastere = -1;

        if(this.cnp[0] == '1')
        {
            this.sex = 'M';
            an_nastere = '1' + '9' + this.cnp[1] + this.cnp[2];
            luna_nastere = this.cnp[3] + this.cnp[4];
            zi_nastere = this.cnp[5] + this.cnp[6];
        }
        else if(this.cnp[0] == '2')
        {
            this.sex = 'F';
            an_nastere = '1' + '9' + this.cnp[1] + this.cnp[2];
            luna_nastere = this.cnp[3] + this.cnp[4];
            zi_nastere = this.cnp[5] + this.cnp[6];
        }
        else if(this.cnp[0] == '5')
        {
            this.sex = 'M';
            an_nastere = '2' + '0' + this.cnp[1] + this.cnp[2];
            luna_nastere = this.cnp[3] + this.cnp[4];
            zi_nastere = this.cnp[5] + this.cnp[6];
        }
        else if(this.cnp[0] == '6')
        {
            this.sex = 'F';
            an_nastere = '2' + '0' + this.cnp[1] + this.cnp[2];
            luna_nastere = this.cnp[3] + this.cnp[4];
            zi_nastere = this.cnp[5] + this.cnp[6];
        }

        let nastere = new Date(an_nastere, luna_nastere, zi_nastere, 0, 0, 0, 0);
        let ageDifMs = Date.now() - nastere.getTime();
        let ageDate = new Date(ageDifMs);
        this.varsta = Math.abs(ageDate.getUTCFullYear() - 1970);
    }
}

class bilet
{
    constructor(obj)
    {
        this.cuvcodv = obj.CUVCODV;
        this.idp = obj.IDP;
        this.db = "";
        if(obj.DB.length == 8)
        {
            this.db = obj.DB.substr(6, 2) + "/" +
                      obj.DB.substr(4, 2) + "/" +
                      obj.DB.substr(0, 4);
        }
        this.rec = obj.REC;
        this.trm = obj.TRM;
        this.orap = obj.ORAP;
        this.pard = obj.PARD;
        this.doc = obj.DOC;
        this.analize = obj.ANALIZE;
    }
}

document.getElementById("rezultate_submit").onclick = () => {
    let cnp = document.getElementById('CNP').value;
    let id = document.getElementById('ID').value;
    CheckBilet(cnp, id);
}

function CheckBilet(cnp, id)
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4) {
            if(this.status == 404)
            {
                alert(this.responseText);
            }
            else if(this.status == 200)
            {           
                resp = JSON.parse(this.responseText);
                Completed(new pacient(resp['pacient']), new bilet(resp['bilet']), resp['grupe']);
            }
        }
    };
    //loading "Cautare bilet"
    xhttp.open("GET", "/get_bilet?cnp=" + cnp + "&id=" + id, true);
    xhttp.send();
}

function isNumeric(n) 
{
    return !isNaN(parseFloat(n)) && isFinite(n);
}

function areNumeric(...numbers)
{
    for(let n of numbers)
        if(isNumeric(n) == false)
            return false;
    return true;
}

function Completed(pacient, bilet, grupe)
{
    //stop loading
    const popup = document.getElementById("rezultate_popup");
    popup.style.width = "100vw";
    popup.style.height = "100vh";
    popup.innerHTML = 
    `<header>
        <div>
            Laborator de Analize  Medicale Dr. ADINA PREDA <br>
            ALEXANDRIA, Str. Libertatii Nr. 122-124 <br>
            Telefon/Fax: 0347804419 Mobil: 0740371897 <br>
            E-mail: adinapreda@gmail.com <br><br>
        </div>
        <img src = 'images/sigla.jpg'></img>
    </header>
    <section id = "rezultate_detalii">
        <h1>Buletin de Analize Medicale ${bilet.cuvcodv}</h1>
        <div id='detalii_pacient'>
            Nume: ${pacient.name}<br>
            C.N.P.: ${pacient.cnp}<br>
            Sex: ${pacient.sex}<br>
            Varsta: ${pacient.varsta} ani <br>
            Adresa:<br>
            Trimis de: ${bilet.doc} (${bilet.pard})<br>
        </div>
        <div id = 'detalii_bilet'>
            Data recoltare: ${bilet.db} &nbsp;&nbsp;
            Data rezultat: ${bilet.db}<br>
            Ora recoltarii/prezentarii: ${bilet.orap}<br>
            Operator: ADINA PREDA<br>
            Punct de recoltare: ${bilet.rec=="T"?"Extern":"Intern"}
        </div>
    </section>
    <main id="rezultate_main">
    </main>
    <footer>
        COD FGL-5.8-01 Editia 1/16.06.2014, Revizia 0/16.06.2014<br>

        NOTA: Se declara ca raportul de analiza se refera numai la obiectul analizat. Reproducerea sau utilizarea buletinului de analize in alte scopuri decat cele pentru care a fost realizat, fara acordul Laborator de Analize Medicale Dr. ADINA PREDA, este interzisa!<br>
        Rezultatele se refera numai la proba analizata. &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; x - Analize neacreditate RENAR<br>
        "!" - Valori in afara limitelor admise pentru varsta si sexul respectiv.
    </footer>
    `;

    const rezTable = document.createElement("table");
    rezTable.setAttribute("class", "rezultate_table");
    document.getElementById("rezultate_main").appendChild(rezTable);
    const tableTitles = ["Denumire Analiza", "Rezultat", "Unitate de masura", "Interval biologic de referinta"];
    AddLine(rezTable, tableTitles, true);

    grupe.sort(function(a, b) {
        return a.CODG - b.CODG;
    });

    for(let i = 0; i < grupe.length; i++)
    {
        AddLine(rezTable, [grupe[i].NUME], false, "cell_grupa");
        for(let j = 0; j < bilet.analize.length; j++)
        {
            const analiza = bilet.analize[j];
            if(analiza.aCodg == grupe[i].CODG)
            {
                const tr = AddLine(rezTable);
                AddCell(tr, analiza.aDen);
                if(     areNumeric(analiza.aVmin, analiza.aVmax, analiza.aRez) 
                    && (parseInt(analiza.aRez) < parseInt(analiza.aVmin) ||
                        parseInt(analiza.aRez) > parseInt(analiza.aVmax) ) )
                {
                    AddCell(tr, analiza.aRez, false, "cell_incorrect");
                }
                else
                    AddCell(tr, analiza.aRez);
                AddCell(tr, analiza.aUma);
                AddCell(tr, analiza.aVmin + " - " + analiza.aVmax);
            }
        }
    }
}

function AddLine(table, content = [], isHeader = false, cellClass = undefined)
{
    const tr = document.createElement("tr");
    for(let i = 0; i < content.length; i++)
        AddCell(tr, content[i], isHeader, cellClass);
    table.appendChild(tr);
    return tr;
}

function AddCell(row, content, isHeader, cellClass)
{
    const td = document.createElement(isHeader ? "th" : "td");
    if(cellClass != undefined)
        td.setAttribute("class", cellClass);
    const text = document.createTextNode(content);
    td.appendChild(text);
    row.appendChild(td);
}