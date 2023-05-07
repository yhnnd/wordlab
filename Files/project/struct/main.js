function factory(Name,Age,Score){
    var s
    s.name=Name
    s.age=Age
    s.score=Score
    return s
}

function structvoid(){
    var s_void=s
    s_void.prototype=s
    s_void.name="tom"
    s_void.age=16
    s_void.score=100
}

function structjson(){
    var s_json={name:"",age:20,score:60}
}

function structConstruct(){
    var s_construct=factory("sam",18,36)
}

function ShowAll(){
    printAllData()
}
