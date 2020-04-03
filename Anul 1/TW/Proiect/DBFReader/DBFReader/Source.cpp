#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <cassert>
#include "dbf.h"
#include "structs.h"
#include "database.h"

using namespace std;

const string dir = "database/";

map<string, pacient> global_pacient;
map<pair<string, string>, bilet> global_bilet;
database db("127.0.0.1:3306", "root", "");

void AddPacient(const pacient &p)
{
	db.AddPacient(p);
}

void AddGrupa(const grupa& g)
{
	db.AddGrupa(g);
}

void AddBilet(const bilet& b)
{
	db.AddBilet(b);
}

void Update()
{
	dbf db_bilet(dir + "bilet.dbf"),
		db_pacient(dir + "pacient.dbf"),
		db_doctor(dir + "doctor.dbf"),
		db_lbilet(dir + "lbilet.dbf"),
		db_lbilete(dir + "lbilete.dbf"),
		db_grupe(dir + "grupe.dbf");

	vector<int> records = db_pacient.getMultipleRecords();
	for (int rec : records)
	{
		pacient p;
		p.cnp = db_pacient.getField(rec, "IDP");
		p.name = db_pacient.getField(rec, "NP");
		AddPacient(p);
	}

	records = db_grupe.getMultipleRecords();
	for (int rec : records)
	{
		grupa g;
		g.codg = db_grupe.getField(rec, "CODG");
		g.name = db_grupe.getField(rec, "DENG");
		AddGrupa(g);
	}

	unordered_map<string, string> map_pard;
	records = db_doctor.getMultipleRecords();
	for (int rec : records)
	{
		string pard = db_doctor.getField(rec, "PARD"),
			   nd	= db_doctor.getField(rec, "ND");
		map_pard[pard] = nd;
	}

	map<pair<string, string>, bilet> map_cuv_codv;
	records = db_bilet.getMultipleRecords();
	for (int rec : records)
	{
		bilet b;
		b.idp = db_bilet.getField(rec, "IDP");
		b.cuv = db_bilet.getField(rec, "CUV");
		b.codv = db_bilet.getField(rec, "CODV");
		b.db = db_bilet.getField(rec, "DB");
		b.rec = db_bilet.getField(rec, "RECEXT");
		b.trm = db_bilet.getField(rec, "TRIMIS");
		b.orap = db_bilet.getField(rec, "ORAPREZ");
		b.pard = db_bilet.getField(rec, "PARD");
		if (b.pard.size() > 1)
			b.doc = map_pard[b.pard];
		map_cuv_codv[make_pair(b.cuv, b.codv)] = b;
	}

	records = db_lbilet.getMultipleRecords();
	for (int rec : records)
	{
		string cuv	= db_lbilet.getField(rec, "CUV"),
			   codv = db_lbilet.getField(rec, "CODV");
		if (map_cuv_codv.find(make_pair(cuv, codv)) == map_cuv_codv.end())
			continue;
		lbilet b;
		b.aDen = db_lbilet.getField(rec, "DENA");
		b.aVmin = db_lbilet.getField(rec, "VMINA");
		b.aVmax = db_lbilet.getField(rec, "VMAXA");
		b.aRez = db_lbilet.getField(rec, "REZULTAT");
		b.aUma = db_lbilet.getField(rec, "UMA");
		b.aCoda = db_lbilet.getField(rec, "CODA");
		b.aCodg = db_lbilet.getField(rec, "CODG");
		
		map_cuv_codv[make_pair(cuv, codv)].analize[b.aCoda] = b;
	}

	records = db_lbilete.getMultipleRecords();
	for (int rec : records)
	{
		string cuv = db_lbilete.getField(rec, "CUV"),
			codv = db_lbilete.getField(rec, "CODV"),
			coda = db_lbilete.getField(rec, "CODA");
		if (map_cuv_codv.find(make_pair(cuv, codv)) == map_cuv_codv.end())
			continue;
		map<string, lbilet>& analize = map_cuv_codv[make_pair(cuv, codv)].analize;
		if (analize.find(coda) == analize.end())
			continue;
		lbilet& b = analize[coda];
		b.sDen.push_back(db_lbilete.getField(rec, "CODE"));
		b.sVmin.push_back(db_lbilete.getField(rec, "VMINE"));
		b.sVmax.push_back(db_lbilete.getField(rec, "VMAXE"));
		b.sRez.push_back(db_lbilete.getField(rec, "REZULTATE"));
		b.sUma.push_back(db_lbilete.getField(rec, "UME"));
	}
	for (auto& p : map_cuv_codv)
		AddBilet(p.second);

	db.commit();
}

int main()
{
	//db.AddPacient(p);
	Update();
	return 0;
}