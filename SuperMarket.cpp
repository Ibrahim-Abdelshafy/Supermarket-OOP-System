#include<iostream>
#include <string>
#include<stdexcept>
#include<vector>
using namespace std;



class Product
{
private:
    int id;
    string name;
    float price;
    int quantity;
public:
    Product():id(0),name("Unknown"),price(0),quantity(0)
    {

    }
    Product(int i,const string& n,float p,int q)
    {   
        
        
        if(p<0)throw 
            invalid_argument("Price Cannot Be Negative");
        if(q<0) 
            throw invalid_argument("Quantity Cannot Be Negative");
        id=i;
        name=n;
        price=p;
        quantity=q;
        
    }
    virtual  float calculateTotal() 
    {
        return price*quantity;
    }
  
  
   int getId() const
   {
    return id;
   }
   string getName() const
   {
    return name;
   }
   float getPrice() const
   {
    return price;
   }
   int getQuantity() const
   {
    return quantity;
   }

   void setPrice(float p)
   {
    if(p<0){
        throw invalid_argument("Price Cannot be Negative");
    }
        price =p;

   }
   void setQuantity(int q)
   {
    if(q<0){
        throw invalid_argument("Quantity Cannot Be Negative");
    }
        quantity=q;
   }
   virtual void display() 
   {
    cout<<"ID: "<<id<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Price: "<<price<<endl;
    cout<<"Quantity: "<<quantity<<endl;
   }
    
    
    virtual ~Product()=default;
    
   
};
class WeightedProduct:public Product
{
private:
    float weightPerUnit;
public:
    WeightedProduct(int i,const string& n,float p,int q,float wpu):Product(i,n,p,q)
    {
        if(wpu<=0){
            throw invalid_argument("Weight Cannot Be Negative");
        }
        weightPerUnit=wpu;
    }
    float calculateTotal() 
    {
        return weightPerUnit*getPrice()*getQuantity();
    }
    void display()
    {
        Product::display();
        cout<<"Weight Per Unit: "<<weightPerUnit<<endl;
    }
};
class DiscountedProduct:public Product
{
private:
    float DiscountPercentage;
public:
    DiscountedProduct(int i,const string& n,float p,int q,float DP):Product(i,n,p,q)
    {
        if(DP<0)
        {
            throw invalid_argument("Discount Percentage Cannot Be Negative");
        }
        if(DP>100)
        {
            throw invalid_argument("Discount Percentage Cannot Be Greater Than 100");
        }
        DiscountPercentage=DP;
    }
    float calculateTotal()
    {
        float total = getPrice() * getQuantity();
        return total - (total * DiscountPercentage / 100);
    }
    void display()
    {
        Product::display();
        cout<<"Discount Percentage is: "<<DiscountPercentage<<endl;
    }

};
class ShoppingCart
{
private:
    vector<Product*> products;
public:
    void addProduct(Product* p)
    {   for(int i=0;i<products.size();i++)
        {
            if(products[i]->getId()==p->getId())
            {
                throw invalid_argument("Product ID Is Already Registerd");
            }
        }
        products.push_back(p);

    }
     void removeProduct(int id)
    {
        for(int i=0;i<products.size();i++)
        {
            if(products[i]->getId()==id)
            {
                delete products[i];
                products.erase(products.begin()+i);
                return;
            }
        }
        throw invalid_argument("Product Not Found");
    }
    void updateQuantity(int id,int newquantity)
    {
        for(int i=0;i<products.size();i++)
        {
            if(products[i]->getId()==id)
            {
                products[i]->setQuantity(newquantity);
                return;
            }

        }
        throw invalid_argument("Product Not Found");
    }
    float calculateGrandTotal()
    {
        float total =0;
        for(Product* p:products)
        {
            total+=p->calculateTotal();
        }
        return total;
    }
   
    void displayAll()
    {
        for(Product* p:products)
        {
            p->display();
        }
    }
    ~ShoppingCart()
    {
        for(Product* p:products)
        {
            delete p;
        }
    }
};

int main()
{
        cout<<"Welcome!"<<endl;
        cout<<"We Hope You Have A Great Time"<<endl;

         ShoppingCart cart;
         int choice;

    do
    {
        cout<<"1.Add Product"<<endl;
        cout<<"2.Remove Product"<<endl;
        cout<<"3.Display Cart"<<endl;
        cout<<"4.Show Grand Total"<<endl;
        cout<<"5.Update Quantity"<<endl;
        cout<<"0.Exit"<<endl;
        cout<<"Enter Choice: "<<endl;

        cin>>choice;
        
    

    try
    
    {
       
        switch (choice)
        {
        case 1:
        {
            int type;
            cout << "Select Product Type:\n";
            cout << "1. Normal Product\n";
            cout << "2. Weighted Product\n";
            cout << "3. Discounted Product\n";
            cout << "Enter type: ";
            cin >> type;

            int id;
            string name;
            float price;
            int quantity;

            cout << "Enter ID: ";
            cin >> id;

            cout << "Enter Name: ";
            cin >> name;

            cout << "Enter Price: ";
            cin >> price;

            cout << "Enter Quantity: ";
            cin >> quantity;

                    if(type == 1)
            {
                cart.addProduct(new Product(id, name, price, quantity));
            }
            else if(type == 2)
            {
                float weight;
                cout << "Enter Weight Per Unit: ";
                cin >> weight;

                cart.addProduct(new WeightedProduct(id, name, price, quantity, weight));
            }
            else if(type == 3)
            {
                float discount;
                cout << "Enter Discount Percentage: ";
                cin >> discount;

                cart.addProduct(new DiscountedProduct(id, name, price, quantity, discount));
            }
            else
            {
                cout << "Invalid type.\n";
            }

            break;
        }
           
        case 2:
            
        {
            int id;
            cout << "Inside remove case\n";
            cout << "Enter ID to remove: ";
            cin >> id;

            cart.removeProduct(id);

            cout << "Product removed successfully.\n";
            break;
        }
            
        case 3:
            cart.displayAll();
                break;
        case 4:
            cout<<"Grand Total: "<<cart.calculateGrandTotal()<<endl;
                break;
        case 5:
                    {
            int id;
            int newQuantity;

            cout << "Enter ID to update: ";
            cin >> id;

            cout << "Enter new quantity: ";
            cin >> newQuantity;

            cart.updateQuantity(id, newQuantity);

            cout << "Quantity updated successfully.\n";
            break;
        }
        case 0:
            cout<<"Exiting..."<<endl;
                break;
        default:
            cout<<"Invalid Choice"<<endl;
        }
        
       
    }
        catch(const exception& e)
        {
            cout<<"Error: "<<e.what()<<endl;
        }
    } while(choice!=0);
        cout<<"Thank You For Shopping With Us"<<endl;
    


    return 0;
}