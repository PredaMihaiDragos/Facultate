class pacient
{
    constructor(obj)
    {
        this.name = obj['Name'];
        this.cnp = obj['CNP'];
        let an_nastere = -1, luna_nastere = -1, zi_nastere = -1;

        if(this.cnp[0] == '1')
        {
            this.sex = 'M';
            an_nastere = '1' + '9' + this.cnp[1] + this.cnp[2];
            luna_nastere = this.cnp[3] + this.cnp[4];
            zi_nastere = this.cnp[5] + this.cnp[6];
        }
        else if(this.cnp[0] == '2')
        {
            this.sex = 'F';
            an_nastere = '1' + '9' + this.cnp[1] + this.cnp[2];
            luna_nastere = this.cnp[3] + this.cnp[4];
            zi_nastere = this.cnp[5] + this.cnp[6];
        }
        else if(this.cnp[0] == '5')
        {
            this.sex = 'M';
            an_nastere = '2' + '0' + this.cnp[1] + this.cnp[2];
            luna_nastere = this.cnp[3] + this.cnp[4];
            zi_nastere = this.cnp[5] + this.cnp[6];
        }
        else if(this.cnp[0] == '6')
        {
            this.sex = 'F';
            an_nastere = '2' + '0' + this.cnp[1] + this.cnp[2];
            luna_nastere = this.cnp[3] + this.cnp[4];
            zi_nastere = this.cnp[5] + this.cnp[6];
        }

        let nastere = new Date(an_nastere, luna_nastere, zi_nastere, 0, 0, 0, 0);
        let ageDifMs = Date.now() - nastere.getTime();
        let ageDate = new Date(ageDifMs);
        this.varsta = Math.abs(ageDate.getUTCFullYear() - 1970);
    }
}

class bilet
{
    constructor(obj)
    {
        this.cuvcodv = obj.CUVCODV;
        this.idp = obj.IDP;
        this.db = "";
        if(obj.DB.length == 8)
        {
            this.db = obj.DB.substr(6, 2) + "/" +
                      obj.DB.substr(4, 2) + "/" +
                      obj.DB.substr(0, 4);
        }
        this.rec = obj.REC;
        this.trm = obj.TRM;
        this.orap = obj.ORAP;
        this.pard = obj.PARD;
        this.doc = obj.DOC;
        this.analize = obj.ANALIZE;
    }
}