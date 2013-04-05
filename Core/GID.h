#ifndef GID_H
#define GID_H

/** This class only purpos is to generate a uniqe global id, nothing else.. */
class GID
{
	private:
		int id;

	public:
		GID() 
		{ 
			static int ID = 1; 
			this->id = ID;
			ID++;
		}  
		int get() const { return id; }
};


#endif

