#pragma once

class Organism;

class Stack
{
private:
	class Element
	{
	private:
		Organism* key;
		Element* next;
	public:
		Element(Organism* _key, Element* _next);
		void setKey(Organism* _key);
		void setNext(Element* _next);
		Organism* getKey() const;
		Element* getNext() const;
	};
	Element* head;
public:
	Stack();
	void push(Organism* key);
	void pop();
	Organism* peek() const;
	bool foundInStack(Organism* org) const;
};

