/*let MainFramePage = {
    "button_acasa":"home.html",
    "button_orar":"orar.html",
    "button_programari":"programari.html",
    "button_despre":"despre.html",
    "button_rezultate":"rezultate.html",
    "button_certificari":"certificari.html",
    "button_chestionar":"chestionar.html",
    "button_contact":"contact.html"
};

var activeMenuButton = "button_acasa";

function UpdateMainFrame(id)
{
    if(!id)
        id = "button_acasa";
    if(id != activeMenuButton)
    {
        let activeClass = "menuButton_active";
        document.getElementById(activeMenuButton).classList.remove(activeClass);
        activeMenuButton = id;
        document.getElementById(activeMenuButton).classList.add(activeClass);

        document.getElementById("mainFrame").contentWindow.location.replace(MainFramePage[id]);
    }
}

function menuButtonClick()
{
    UpdateMainFrame(this.id);
}
*/
let navbar, body, sticky;

function init()
{
    navbar = document.getElementById("navbar");
    sticky = 150;
    Scroll();
}

window.onscroll = function() {Scroll()};

function Scroll() 
{
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