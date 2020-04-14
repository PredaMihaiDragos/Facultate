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
    HideCertificare();
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

function ShowCertificare(url)
{
    const img = document.createElement("img");
    img.src = url;
    certificariModal.appendChild(img);
    certificariModal.style.display = "block";
}

function HideCertificare()
{
    while(certificariModal.firstChild)
      certificariModal.lastChild.remove();
    certificariModal.style.display = "none";
}