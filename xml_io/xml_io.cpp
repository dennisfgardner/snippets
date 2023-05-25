/*
This file was written by Dennis Gardner and the UNLICENSE applies to this code.
However, I use tinyxml2 which is under the zlib license. See tinyxml2 header or
source for its author and license details.
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include "tinyxml2.h"

using std::cout;
using std::endl;
using std::string;
using tinyxml2::XMLElement;


struct HouseInfo{
    string address;
    float asking_price;
    int bedrooms;
    float bathrooms;
};


int xml_read(){
    tinyxml2::XMLDocument doc;
    
    FILE* fp = fopen("car_inventory.xml", "r");
	doc.LoadFile(fp);

    XMLElement* p_root = doc.RootElement();
    XMLElement* p_child = p_root->FirstChildElement("car");

    std::vector<const char*> tags = {"type", "EV"};
    while(p_child){
        for (std::size_t i{}; i < tags.size(); ++i){
            XMLElement* ptr = p_child->FirstChildElement(tags[i]);
            cout << tags[i] << ":" << ptr->GetText() << "\n";
            cout << ( i == tags.size() - i ? "\n" : "");
        }
        p_child = p_child->NextSiblingElement("car");
    }    
    return 0;
}

int xml_write(){
    tinyxml2::XMLDocument doc;

    HouseInfo house1;
    house1.address = "1234 Main St";
    house1.asking_price = 100000;
    house1.bedrooms = 4;
    house1.bathrooms = 2.5;

    HouseInfo house2;
    house2.address = "4321 1st St";
    house2.asking_price = 150000;
    house2.bedrooms = 3;
    house2.bathrooms = 3;

    std::vector<HouseInfo> houses_for_sale = {house1, house2};

    cout << "Writing Houses for Sale" << "\n";
    tinyxml2::XMLNode* pRoot = doc.NewElement("houses");
    doc.InsertFirstChild(pRoot);

    for (auto h : houses_for_sale){
        cout << "adding a house" << "\n";
        cout << "\t" << h.address << "\n";
        cout << "\t" << h.asking_price << "\n";
        cout << "\t" << h.bedrooms << "\n";
        cout << "\t" << h.bathrooms << "\n";

        XMLElement* pHouse = doc.NewElement("house");
        pRoot->InsertFirstChild(pHouse);
        XMLElement* pAddress = doc.NewElement("address");
        pAddress->SetText(h.address.c_str());
        pHouse->InsertEndChild(pAddress);

        XMLElement* pAskPrice = doc.NewElement("askingPrice");
        pAskPrice->SetText(h.asking_price);
        pHouse->InsertEndChild(pAskPrice);

        XMLElement* pBedrooms = doc.NewElement("bedrooms");
        pBedrooms->SetText(h.bedrooms);
        pHouse->InsertEndChild(pBedrooms);

        XMLElement* pBathrooms = doc.NewElement("bathrooms");
        pBathrooms->SetText(h.bathrooms);
        pHouse->InsertEndChild(pBathrooms);

        pRoot->InsertEndChild(pHouse);
    }

    doc.SaveFile("houses_for_sale.xml");
    return 0;
}

int main(){
    cout << "XML Demonstration\n" << endl;
    xml_read();
    xml_write();
    cout << "Demo Over" << endl;
}
