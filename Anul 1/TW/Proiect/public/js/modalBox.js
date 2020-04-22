const chestionarModal = document.getElementById("chestionarBox");
const certificariModal = document.getElementById("certificariBox");

document.getElementById("chestionarClose").onclick = function() {
  HideChestionar();
}

document.getElementById("certificariClose").onclick = function() {
  HideCertificare();
}

window.onclick = function(event) {
  if (event.target == chestionarModal) {
    HideChestionar();
  }
  else if(event.target == certificariModal) {
    HideCertificare();
  }
}

window.ontouchstart = function(event) {
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

let certificareImg;
function ShowCertificare(url)
{
    const img = document.createElement("img");
    img.src = url;
    certificareImg = certificariModal.appendChild(img);
    certificariModal.style.display = "block";
}

function HideCertificare()
{
    certificareImg.remove();
    certificariModal.style.display = "none";
}