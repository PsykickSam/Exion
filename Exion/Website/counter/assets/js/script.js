var counter = document.querySelector(".counter");
counter.innerHTML = "0";

function clickme() {
    var countData = counter.innerHTML;
    var countNumber = parseInt(countData);

    countNumber += 1;
    counter.innerHTML = countNumber + "";
}