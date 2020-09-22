#include <iostream>
#include "Stack.h"

Stack::Stack()
	:head(NULL)
{ }

Stack::Element::Element(Organism* _key, Element* _next)
	: key(_key), next(_next)
{}

void Stack::Element::setKey(Organism* _key)
{
	key = _key;
}

Organism* Stack::Element::getKey() const
{
	return key;
}

void Stack::Element::setNext(Element* _next)
{
	next = _next;
}

Stack::Element* Stack::Element::getNext() const
{
	return next;
}

void Stack::push(Organism* key)
{
	if (key == NULL)
		return;
	Element* new_elem = new Element(key, head);
	head = new_elem;
}

void Stack::pop()
{
	Element* temp = head;
	head = head->getNext();
	if (temp != NULL)
		delete temp;
}

Organism* Stack::peek() const
{
	if (head == NULL)
		return NULL;
	return head->getKey();
}

bool Stack::foundInStack(Organism* org) const
{
	Element* temp = head;
	while (temp != NULL)
	{
		if (temp->getKey() == org)
			return true;
		temp = temp->getNext();
	}
	return false;
}