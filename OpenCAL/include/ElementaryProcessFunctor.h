
#ifndef ELEMENTARYPROCESS_H_
#define ELEMENTARYPROCESS_H_



class ElementaryProcessFunctor {

public:
	ElementaryProcessFunctor();
	virtual void run(struct CALModel2D* model, int i, int j) 		=0;
	virtual void run(struct CALModel3D* model, int i, int j, int k) =0;

	void operator()(CALModel2D* model, int i, int j);
	void operator()(CALModel3D* model, int i, int j, int k);

	virtual ~ElementaryProcessFunctor();
};


#endif /* ELEMENTARYPROCESS_H_ */
