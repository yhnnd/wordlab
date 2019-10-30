// call this before init_dark_mode()
function init_dark_mode_start(){
    var backgroundColor = "#fff";
    if(localStorage.is_dark_mode=="true"){
        backgroundColor = "rgb(37, 40, 48)";
    }
    document.write(
        "<div id='style-mode-progress' \
        data-style='no-support' \
        style='\
        background:"+backgroundColor+";\
        opacity:1;\
        position:fixed;\
        top:0;\
        left:0;\
        z-index:10000;\
        width:100%;\
        height:"+window.innerHeight+"px;\
        transition:opacity .3s ease;\
        '></div>"
    );
}

init_dark_mode_start();