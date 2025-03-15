var x = new Audio("../assets/thanks.mp3");

function thanksL(){
    var z = document.getElementById("submitButtonL");
    z.remove();

    const thx = `<p>Thanks for your submission !</p>`;
    const container = document.getElementById("containerL");
    container.innerHTML = thx;
    x.play();
}
function thanksR(){
    var z = document.getElementById("submitButtonR");
    z.remove();

    const thx = `<p>Thanks for your submission !</p>`;
    const container = document.getElementById("containerR");
    container.innerHTML = thx;
    x.play();
}