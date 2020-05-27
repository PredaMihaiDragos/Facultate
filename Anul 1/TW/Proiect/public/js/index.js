let navbar, body;
let loaded = false;

const menuButtons = {
    "mainButton":"main", 
    "programariButton":"programari",
    "rezultateButton":"rezultate",
    "certificariButton":"certificari"
};

function Post(url, str = "")
{
    const xhttp = new XMLHttpRequest();
    xhttp.open("POST", url, true);
    xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhttp.send(str);
}

function init()
{
    navbar = document.getElementById("navbar");
    
    loaded = true;
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

function GetScrollPosition(id)
{
    const element = document.getElementById(id);
    const navOffset = parseInt(getComputedStyle(document.body).getPropertyValue('--nav-height'));
    const style = window.getComputedStyle(element);
    const marginTop = style.getPropertyValue('margin-top'); 
    const elementPosition = element.offsetTop - parseInt(marginTop);
    const offsetPosition = elementPosition - navOffset;
    return Math.max(offsetPosition, 0);
}

let activeButton = "";
function SetActiveButton(bt)
{
    if(activeButton == bt)
        return;
    activeButton = bt;
    for (const [key, value] of Object.entries(menuButtons))
    {
        if(activeButton == key)
            document.getElementById(key).classList.add("active");
        else
            document.getElementById(key).classList.remove("active");
    }
    setTimeout(function() { 
        if(activeButton == bt) //daca am stat cel putin 1 sec pe sectiune
        {
            Post("sectionView", "section=" + menuButtons[activeButton]);
        }
     }, 1000);
}
function Scroll() 
{
    if(!loaded)
        return;
    const sticky = parseInt(getComputedStyle(document.body).getPropertyValue('--header-height'));
    const y = window.pageYOffset;
    if (y >= sticky) 
    {
        navbar.classList.add("sticky");
        isSticky = false;
    } 
    else if(y < sticky)
    {
        navbar.classList.remove("sticky");
        isSticky = true;
    }
    
    let distMin = Number.POSITIVE_INFINITY;
    let active;
    for (const [key, value] of Object.entries(menuButtons))
    {
        let pos = GetScrollPosition(value);
        if(Math.abs(y-pos) < distMin)
        {
            distMin = Math.abs(y-pos);
            active = key;
        }
    }
    SetActiveButton(active);
}

function scrollToTarget(id)
{
    window.scrollTo({
         top: GetScrollPosition(id),
         behavior: "smooth"
    });
}

function menuButton(id)
{
    scrollToTarget(menuButtons[id]);
}

document.getElementById("submitResults").addEventListener('submit', GetResults);

function GetResults(e)
{
    e.preventDefault();
    const id = encodeURIComponent(document.getElementById("rezultate_id").value);
    const cnp = encodeURIComponent(document.getElementById("rezultate_cnp").value);
    const pdfWindow = window.open("/get_bilet?cnp="+cnp+"&id="+id);
}

let startChestionar;
function ChestionarClick()
{
    startChestionar = Date.now();
    console.log(startChestionar);
    Post("/chestionarClick");
    ShowChestionar();
}

document.getElementById('submitChestionar').onclick = function()
{
    const xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() 
    {
        if (this.readyState == 4) 
        {
            if(this.status == 201)
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
                Info("Raspunsurile tale au fost primite. Multumim!");
                HideChestionar();
            }
            else
                Error(xhttp.responseText);
        }
    };
    let time = Date.now() - startChestionar;
    xhttp.open("PUT", "/chestionar", true);
    xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhttp.send("cnp="+cnp+"&parere="+parere+"&calitate="+calitate+
               "&pret="+pret+"&promptitudine="+promptitudine+"&timp="+time);
};

document.getElementById('resetChestionar').onclick = function()
{
    const cnp = encodeURIComponent(document.getElementById("chestionarCnp").value);
    localStorage.setItem("chestionarCnp", "");
    localStorage.setItem("parere", 2);
    localStorage.setItem("calitate", 2);
    localStorage.setItem("pret", 2);
    localStorage.setItem("promptitudine", 2);
    loadLocalStorage();

    const xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() 
    {
        if (this.readyState == 4) 
        {
            if(this.status == 201)
            {
                Info("Raspunsurile tale au fost resetate.");
            }
            else
                Error(xhttp.responseText);
        }
    };
    xhttp.open("DELETE", "/delete_chestionar", true);
    xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhttp.send("cnp="+cnp);
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
                Info("Programarea a fost realizata cu succes!");
            }
            else
                Error(xhttp.responseText);
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
};