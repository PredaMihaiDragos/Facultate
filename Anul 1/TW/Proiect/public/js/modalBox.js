const chestionarModal = document.getElementById("chestionarBox");
const certificariModal = document.getElementById("certificariBox");

document.getElementById("chestionarClose").onclick = function() {
  HideChestionar();
}

window.onclick = function(event) {
  if (event.target == chestionarModal) {
    HideChestionar();
  }
  else if(event.target == certificariModal) {
    HideCertificari();
  }
}

function ShowChestionar()
{
    chestionarModal.style.display = "block";
}

function HideChestionar()
{
    chestionarModal.style.display = "none";
}

function ShowCertificari(url)
{
    certificariModal.style.display = "block";
}

function HideCertificari()
{
    certificariModal.style.display = "none";
}