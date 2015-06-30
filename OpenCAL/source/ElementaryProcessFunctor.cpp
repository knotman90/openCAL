#include<ElementaryProcessFunctor.h>

 void ElementaryProcessFunctor:: operator()(struct CALModel2D* model, int i, int j){
	this->run(model,i,j);
}

 void ElementaryProcessFunctor:: operator()(struct CALModel3D* model, int i, int j, int k){
	this->run(model,i,j,k);
}

 ElementaryProcessFunctor::ElementaryProcessFunctor() {

}

 ElementaryProcessFunctor::~ElementaryProcessFunctor() {

}

