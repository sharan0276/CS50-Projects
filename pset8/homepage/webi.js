let nav = document.querySelector(".nav-links");
let burger = document.querySelector(".burger");
let links = document.querySelectorAll(".nav-link li");

burger.onclick = function(){
    nav.classList.toggle("nav-active");
    };

links.forEach((link) => {
    link.style.animation = "navLinkFade 0.5s ease fowards ${index / 7 + 0.3}s";
});


function bgChange(){
    /*console.log('working');   for test if it displays along the console*/
    /*this.innerheight gives the height of the screen*/
    if(this.scrollY > this.innerHeight / 2){
        document.body.classList.add("bg-active");
    }
    else{
        document.body.classList.remove("bg-active");
    }
}


const app = ()=>{
    window.addEventListener("scroll", bgChange);
};

app();