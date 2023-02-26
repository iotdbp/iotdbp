$(function () {

    $(".ci").on('click', function () {

        var id = this.id;
        var num = id.slice(3);
        var p_tit = "tit_" + num;
        var p_id = "#" + p_tit;

        $('html,body').animate({
            scrollTop: $(p_id).offset().top
        }, 800);


    });

    var scrollTopFB = $("#scrollTopFB");
    // When the user scrolls down 20px from the top of the document, show the button
    //window.onscroll = function () { scrollFunction() };

    $(window).on('scroll',scrollFunction());

    
});


function scrollFunction() {
    if ($('body').scrollTop > 20 || $(document.documentElement).scrollTop > 20) {
        scrollTopFB.css("display", "block");
    } else {
        scrollTopFB.css("display", "none");
    }
}


function topFunction() {
    $(function () {
        $('html,body').animate({
            scrollTop: $("nav").offset().top
        }, 800);
    });
}

// When the user clicks on the button, scroll to the top of the document
// function topFunction() {
//     document.body.scrollTop = 0;
//     document.documentElement.scrollTop = 0;
// }

// var scrollTopFB = document.getElementById("scrollTopFB");
// // When the user scrolls down 20px from the top of the document, show the button
// window.onscroll = function () { scrollFunction() };

// function scrollFunction() {
//     if (document.body.scrollTop > 20 || document.documentElement.scrollTop > 20) {
//         scrollTopFB.style.display = "block";
//     } else {
//         scrollTopFB.style.display = "none";
//     }
// }

// // When the user clicks on the button, scroll to the top of the document
// function topFunction() {
//     document.body.scrollTop = 0;
//     document.documentElement.scrollTop = 0;
// }
