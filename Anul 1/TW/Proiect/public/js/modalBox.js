const chestionarModal = document.getElementById("chestionarBox");

document.getElementById("chestionarClose").onclick = function() {
  HideChestionar();
}

window.onclick = function(event) {
  if (event.target == chestionarModal) {
    HideChestionar();
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