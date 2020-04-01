class lbilet
{
    constructor()
    {   
       this.aDen = "";
       this.aVmin = "";
       this.aVmax = "";
       this.aRez = "";
       this.aUma = "";
       this.aCoda = "";
       this.aCodg = "";

       this.sDen = [];
       this.sVmin = [];
       this.sVmax = [];
       this.sRez = [];
       this.sUma = [];
    }
}

class bilet
{
    constructor()
    {
        this.idp = "";
        this.cuv = "";
        this.codv = "";
        this.db = "";
        this.rec = "";
        this.trm = "";
        this.orap = "";
        this.pard = "";
        this.doc = "";

        this.analize = []
    }
}

module.exports.lbilet = lbilet;
module.exports.bilet = bilet;