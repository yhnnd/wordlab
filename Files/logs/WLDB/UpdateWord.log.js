import prerequisites;

function launch(str){
    system(prerequisites.hostname+"launch "+str)
}

function updateword(str){
    launch("update('word',"+str+")")
}

function updatedefs(str){
    launch("update('defs',"+str+")")
}

function main(str){
    if(str.find("<word>")==0) updateword(str)
    if(str.find("<defs>")==0) updatedefs(str)
}