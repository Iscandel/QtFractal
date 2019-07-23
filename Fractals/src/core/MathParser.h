#pragma once
#include <string>

#include "FParser\fparser.hh"

class MathParser
{
public:
	MathParser() {}

	MathParser(const std::string& expr, const std::string& vars = "")
	{
		myExpr = expr;
		myVars = vars;
		if (vars == "")
			myVars = "zn, zprev, zpprev, c";
		
		myParser.Parse(myExpr, myVars);

		myParser.Optimize();
	}

	MathParser(const MathParser& p)
	{
		myId = p.myId;
		myVars = p.myVars;
		myName = p.myName;
		myExpr = p.myExpr;
		myParser.Parse(myExpr, myVars);
		myParser.Optimize();
	}

	MathParser& operator=(const MathParser& p)
	{
		myId = p.myId;
		myVars = p.myVars;
		myName = p.myName;
		myExpr = p.myExpr;
		myParser.Parse(myExpr, myVars);
		myParser.Optimize();

		return *this;
	}


	void setId(int id)
	{
		myId = id;
	}

	int getId() const
	{
		return myId;
	}

	void setName(const std::string& name) {
		myName = name;
	}

	~MathParser();

	void preprocess()
	{

	}

	void init();
	//template<class ...Args>
	//void eval(Args&&...args);

	template<class T>
	T eval(T* args)
	{
		return myParser.Eval(args);
	}
	std::string getExpr() { return myExpr; }

protected:
	FunctionParser_cd myParser;

	int myId;
	std::string myName;
	std::string myVars;
	std::string myExpr;
};

