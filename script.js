$(function(){

    $(".ci").on('click',function() {

        // var p_id = await getit(this);

        var id = this.id;
        var num = id.slice(3);
        var p_tit = "tit_"+num;
        var p_id = "#"+p_tit;
      
        console.log(p_id);

        // $('html,body').animate({
        //     scrollTop: $("#tit_2_3").offset().top
        // }, 1000);

        $('html,body').animate({
            scrollTop: $(p_id).offset().top
        }, 1000);


    });
});
