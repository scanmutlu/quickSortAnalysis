#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;


class usData{
    unsigned long population;
    string minimum_age;
    string maximum_age;
    string gender;
    unsigned long zipcode;
    string geo_id;
public:
    ~usData(){};
    usData(unsigned long pop, string minAge,string maxAge, string genre, unsigned long zip, string geo);
    unsigned long getPopulation();
    string getMinAge();
    string getMaxAge();
    string getGender();
    unsigned long getZipCode();
    string getGeoId();
};

usData::usData(unsigned long pop, string minAge, string maxAge, string genre, unsigned long zip, string geo) {
    population = pop;
    minimum_age = minAge;
    maximum_age = maxAge;
    gender = genre;
    zipcode = zip;
    geo_id = geo;
}

unsigned long usData::getPopulation() {
    return population;
}
string usData::getMinAge() {
    return minimum_age;
}

string usData::getMaxAge() {
    return maximum_age;
}

string usData::getGender(){
    return gender;
}

unsigned long usData::getZipCode() {
    return zipcode;
}

string usData::getGeoId() {
    return geo_id;
}
void outTextFile(vector<usData> arr);
void printVector(vector<usData> arr);
void quickSort(vector<usData> &arr, long p,long q);
long partition(vector<usData> &arr, long p, long r);

int main(int argc, char *argv[]) {

    vector<usData> usDataVector;
    ifstream file("population_by_zip_2010.csv");
    if(file == NULL) cout << "File cannot opened" ;
    string line;
    string temp;
    unsigned long population = 0;
    string minimum_age = "";
    string maximum_age = "";
    string gender;
    unsigned long zipcode = 0;
    string geo_id;
    unsigned long counter = 0;
    unsigned long argCounter = atol(argv[1]);
    while (counter<= argCounter){
        getline(file,line);
        gender = "";
        temp = "";
        istringstream isStream(line);
        getline(isStream, temp,',');
        istringstream pop(temp);
        pop>>population;
        temp = "";
        getline(isStream,minimum_age ,',');
        getline(isStream, maximum_age, ',');
        getline(isStream, gender, ',');
        getline(isStream, temp, ',');
        istringstream zip(temp);
        zip>> zipcode;
        getline(isStream, geo_id, ',');
        if(counter == 0){
            counter++;
            continue;
        }
        usData usData1(population,minimum_age,maximum_age,gender,zipcode,geo_id);
        usDataVector.push_back(usData1);
        //cout << counter<< "\t"<<usData1.getPopulation() <<","<<usData1.getMinAge()<<"," <<usData1.getMaxAge()<<","<<usData1.getGender()<<","<<usData1.getZipCode()<<usData1.getGeoId() << endl;
        counter++;
    }
    clock_t time;
    time = clock();
    quickSort(usDataVector,0,usDataVector.size()-1);
    //printVector(usDataVector);
    time = clock() - time;
    cout << "Elapsed Time: " << ((float) time) / CLOCKS_PER_SEC << endl;
	outTextFile(usDataVector);
    return 0;
}

void quickSort(vector<usData> &arr, long p,long r){
    long q;
    if(p<r)
    {
        q=partition(arr, p,r);
        quickSort(arr,p,q-1);
        quickSort(arr,q+1,r);
    }
}



long partition(vector<usData> &arr, long p, long r){
    {
        usData x= arr[r];
        long i=p-1;
        long j = 0;
        for(j=p; j<r-1; j++)
        {
            if(arr[j].getPopulation() < x.getPopulation())
            {
                i=i+1;
                swap(arr[i],arr[j]);
            }else if(arr[j].getPopulation() == x.getPopulation() && arr[j].getGeoId().compare(x.getGeoId())<0){
                i = i+1;
                swap(arr[i],arr[j]);
            }

        }
					
        swap(arr[i+1],arr[r]);
        return i + 1;
    }

}

void printVector(vector<usData> arr){
    int size = arr.size();
    for (int i = 0; i < size; i++){
        cout << i << '\t';
        cout << arr[i].getPopulation() << '\t';
        cout << arr[i].getMinAge() << '\t';
        cout << arr[i].getMaxAge() << '\t';
        cout << arr[i].getGender() << '\t';
        cout << arr[i].getZipCode() << '\t';
        cout << arr[i].getGeoId() << endl;
    }
}


void outTextFile(vector<usData> arr){
	ofstream outfile;
	outfile.open("Output.csv");
	int size = arr.size();
	for (int i = 0; i <= size-1; i++){
		outfile << i << ',';
		outfile << arr[i].getPopulation() << ',';
		outfile << arr[i].getMinAge()<< ',';
		outfile << arr[i].getMaxAge() << ',';
		outfile << arr[i].getGender() << ',';
		outfile << arr[i].getZipCode() << ',';
		outfile << arr[i].getGeoId() << endl;

	}
}

