let nav = document.querySelector(".nav-links");
let burger = document.querySelector(".burger");
let links = document.querySelectorAll(".nav-link li");

burger.onclick = function(){
    nav.classList.toggle("nav-active");
    };

links.forEach((link) => {
    link.style.animation = "navLinkFade 0.5s ease fowards ${index / 7 + 0.3}s";
});