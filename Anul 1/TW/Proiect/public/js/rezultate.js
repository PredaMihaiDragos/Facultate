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

document.getElementById("button_submit").onclick = () => {
    let cnp = document.getElementById('CNP').value;
    let id = document.getElementById('ID').value;
    CheckBilet(cnp, id);
}

CheckBilet("1910923340440", "3-2498");

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

function Completed(pacient, bilet, grupe)
{
    //stop loading
    document.getElementById("form_div").style.display = "none";
    document.getElementById("rezultate").innerHTML = 
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
    document.getElementById("rezultate_main").appendChild(rezTable);
    const tableTitles = ["Denumire Analiza", "Rezultat", "Unitate de masura", "Interval biologic de referinta"];
    const tableHeader = document.createElement("tr");
    for(let i = 0; i < tableTitles.length; i++)
    {
        const title = document.createElement("th");
        const content = document.createTextNode(tableTitles[i]);
        title.appendChild(content);
        tableHeader.appendChild(title);
    }                                        
    rezTable.appendChild(tableHeader);

    grupe.sort(function(a, b) {
        return a.CODG - b.CODG;
    });

    for(let i = 0; i < grupe.length; i++)
    {
        const tr = document.createElement("tr");
        const content = document.createTextNode(grupe[i].NUME);
        tr.appendChild(content);
        rezTable.appendChild(tr);

        for(let j = 0; j < bilet.length; j++)
        {
            if(bilet.codg == grupe[i].CODG)
            {

            }
        }
    }
}

function AddLine(table, content)
{
    const tr = document.createElement("tr");
    table.appendChild(tr);
    return tr;
}