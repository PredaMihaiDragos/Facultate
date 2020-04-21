let navbar, body;


function init()
{
    navbar = document.getElementById("navbar");
    
    Scroll();
    initStarRating();
    loadLocalStorage();
}

function loadLocalStorage()
{
    document.getElementById("chestionarCnp").value = localStorage.getItem("chestionarCnp");
    starRating.get("parere").SetStars(localStorage.getItem("parere"));
    starRating.get("calitate").SetStars(localStorage.getItem("calitate"));
    starRating.get("pret").SetStars(localStorage.getItem("pret"));
    starRating.get("promptitudine").SetStars(localStorage.getItem("promptitudine"));
}

window.onscroll = function() {Scroll()};

function Scroll() 
{
    const sticky = parseInt(getComputedStyle(document.body).getPropertyValue('--header-height'));
    if (window.pageYOffset >= sticky) 
    {
        navbar.classList.add("sticky");
        isSticky = false;
    } 
    else if(window.pageYOffset < sticky)
    {
        navbar.classList.remove("sticky");
        isSticky = true;
    }
}

function scrollToTarget(id)
{
    const element = document.getElementById(id);
    const headerOffset = 70;
    const style = window.getComputedStyle(element);
    const marginTop = style.getPropertyValue('margin-top'); 
    const elementPosition = element.offsetTop - parseInt(marginTop);
    const offsetPosition = elementPosition - headerOffset;

    window.scrollTo({
         top: offsetPosition,
         behavior: "smooth"
    });
}

document.getElementById("submitResults").addEventListener('submit', GetResults);

function GetResults(e)
{
    e.preventDefault();
    const id = encodeURIComponent(document.getElementById("rezultate_id").value);
    const cnp = encodeURIComponent(document.getElementById("rezultate_cnp").value);
    const pdfWindow = window.open("/get_bilet?cnp="+cnp+"&id="+id);
}

document.getElementById('submitChestionar').onclick = function()
{
    const cnp = encodeURIComponent(document.getElementById("chestionarCnp").value);
    const parere = encodeURIComponent(starRating.get("parere").GetStars());
    const calitate = encodeURIComponent(starRating.get("calitate").GetStars());
    const pret = encodeURIComponent(starRating.get("pret").GetStars());
    const promptitudine = encodeURIComponent(starRating.get("promptitudine").GetStars());

    localStorage.setItem("chestionarCnp", cnp);
    localStorage.setItem("parere", parere);
    localStorage.setItem("calitate", calitate);
    localStorage.setItem("pret", pret);
    localStorage.setItem("promptitudine", promptitudine);

    const xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() 
    {
        if (this.readyState == 4) 
        {
            if(this.status == 201)
            {
                alert("Raspunsurile tale au fost primite. Multumim!");
                HideChestionar();
            }
            else
                alert(xhttp.responseText);
        }
    };
    xhttp.open("PUT", "/chestionar", true);
    xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhttp.send("cnp="+cnp+"&parere="+parere+"&calitate="+calitate+"&pret="+pret+"&promptitudine="+promptitudine);
};

document.getElementById('submitProgramari').onclick = function()
{
    const nume = encodeURIComponent(document.getElementById("programari_nume").value);
    const telefon = encodeURIComponent(document.getElementById("programari_telefon").value);
    const email = encodeURIComponent(document.getElementById("programari_email").value);
    const mesaj = encodeURIComponent(document.getElementById("programari_mesaj").value);

    const xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() 
    {
        if (this.readyState == 4) 
        {
            if(this.status == 201)
            {
                alert("Programare realizata cu succes!");
            }
            else
                alert(xhttp.responseText);
        }
    };
    xhttp.open("POST", "/programari", true);
    xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhttp.send("nume="+nume+"&telefon="+telefon+"&email="+email+"&mesaj="+mesaj);

    document.getElementById("programari_nume").value = "";
    document.getElementById("programari_telefon").value = "";
    document.getElementById("programari_email").value = "";
    document.getElementById("programari_mesaj").value = "";
}

window.onresize = function() {
    const main = document.getElementById("main");
    //console.log(main.clientHeight);
};