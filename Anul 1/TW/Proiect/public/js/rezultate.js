document.getElementById("button_submit").onclick = () => {
    let cnp = document.getElementById('CNP').value;
    let id = document.getElementById('ID').value;
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4) {
            if(this.status == 404)
            {
                alert(this.responseText);
            }
            else if(this.status == 200)
            {            
                CheckBilet(cnp, id, JSON.parse(this.responseText));
            }
        }
    };
    //start loading "Cautare pacient"
    xhttp.open("GET", "/get_pacient?cnp=" + cnp, true);
    xhttp.send();
}

function CheckBilet(cnp, id, pacient)
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
                Completed(pacient, JSON.parse(this.responseText));
            }
        }
    };
    //loading "Cautare bilet"
    xhttp.open("GET", "/get_bilet?cnp=" + cnp + "&id=" + id, true);
    xhttp.send();
}

function Completed(pacient, bilet)
{
    //stop loading
    bilet.ANALIZE = JSON.parse(bilet.ANALIZE);
}