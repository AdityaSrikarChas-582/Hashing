#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

template<class T>
class HashSet {
private:
    T ElementsCount;
    T Capacity;
    vector<list<T>>HashTable=vector<list<T>>();

    double LoadFactor;
    static const double THRESHOLD;

    void updateLoadFactor() {
        LoadFactor=(double)ElementsCount/(double)Capacity;
    }
    bool needToRehash() {
        return LoadFactor>=THRESHOLD;
    }
    T f1(T x) {
        T sum=0,factor=Capacity;
        while(x!=0) {
            sum=(sum+(x%10)*factor)%Capacity;
            factor++;
            x/=10;
        }
        return sum;
    }
    T f2(T x) {
        T sum=0,factor=Capacity;
        while(x!=0) {
            T d=x%10;
            sum=(sum+d*d*factor)%Capacity;
            factor++;
            x/=10;
        }
        return sum;
    }
    T getHashValue(T x) {
        return (f1(f2(x))+f2(f1(x)))%Capacity;
    } 
public:
    HashSet(T Capacity=100) {
        ElementsCount=0;
        this->Capacity=Capacity;
        LoadFactor=0;
        for(T i=0;i<Capacity;i++) {
            list<T>Bucket=list<T>();
            HashTable.push_back(Bucket);
        }
    }
    static HashSet rehash(HashSet obj) {
        T Capacity=2*(obj.Capacity);
        T ElementsCount=obj.ElementsCount;
        
        HashSet temp=HashSet(Capacity);
        
        for(auto Bucket:obj.HashTable) {
            if(!Bucket.empty()) {
                for(int ele:Bucket) temp.insert(ele); 
            }
        }
        return temp;
    }
    void insert(T ele) {
        T idx=getHashValue(ele);
        HashTable[idx].push_front(ele);
        ElementsCount++;
        updateLoadFactor();
        std::cout<<"Element Added"<<endl;

        if(needToRehash()) {
            *this=rehash(*this);
            std::cout<<"Rehashing Done!"<<endl;
        }
    }
    bool search(T ele) {
        T idx=getHashValue(ele);
        if(HashTable[idx].empty()) {
            return false;
        }
        else {
            auto it=find(HashTable[idx].begin(),HashTable[idx].end(),ele);
            if(it!=HashTable[idx].end()) return true;
            return false;
        }
    }
    void Delete(T ele) {
        T idx=getHashValue(ele);
        auto it=find(HashTable[idx].begin(),HashTable[idx].end(),ele);

        if(it==HashTable[idx].end()) {
            std::cout<<"Not Found"<<endl;
        }
        else {
            HashTable[idx].erase(it);
            std::cout<<"Element Deleted"<<endl;
        }
    }
};

template<typename T>
const double HashSet<T>::THRESHOLD=0.75;

int main() {
    
    long long Capacity;
    
    std::cout<<"Enter Initial Capacity of Hash Table : ";
    std::cin>>Capacity;

    HashSet<long long> obj=HashSet<long long>(Capacity);

    int ch,ele;
    while(1) {
        std::cout<<"1. Add Value"<<endl;
        std::cout<<"2. Search Value"<<endl;
        std::cout<<"3. Delete Value"<<endl;
        std::cout<<"4. QUIT"<<endl;
        std::cout<<"\nEnter Your Choice : ";
        std::cin>>ch;

        switch(ch) {
            case 1:std::cout<<"Enter Element : ";
                   std::cin>>ele;
                   obj.insert(ele);
                   break;
            case 2:std::cout<<"Enter Element : ";
                   std::cin>>ele;
                   if(obj.search(ele)) std::cout<<"Found"<<endl;
                   else std::cout<<"Not Found"<<endl;
                   break;
            
            case 3:std::cout<<"Enter Element : ";
                   std::cin>>ele;
                   obj.Delete(ele);
                   break;
            
            case 4:exit(0);

            default:std::cout<<"Invalid Choice"<<endl;
        }
        std::cout<<endl;
    }
    return 0;
}