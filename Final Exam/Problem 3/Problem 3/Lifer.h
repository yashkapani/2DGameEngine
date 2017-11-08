#pragma once
class Lifer
{
private:
	
	bool			has_procreated;
	int				loc_x;
	int				loc_y;

	
	unsigned int	children;

public:
	unsigned int	lifetime;
		Lifer();
	Lifer(unsigned int children, unsigned int lifetime, int locX, int locY, bool hasProc);
	~Lifer();
	 void updatex(int i_x){ loc_x = loc_x+i_x; }
	 void setx(int i_x){ loc_x=i_x;}
	int getx(){ return loc_x; }
	 void updatey(int i_y){ loc_y = loc_y+i_y; }
	void sety(int i_y){ loc_y=i_y;}
	int gety(){ return loc_y; }
	void setProc(bool proc){has_procreated = proc; }
	bool getProc(){ return has_procreated; }
	void updateChild(unsigned int i_child){ children = children+i_child; }
	void setChild(unsigned int i_child){children = i_child; }
	int getChild(){ return children; }

	//inline void setLife(unsigned int change){ m_Lifetime += change; }
	void setLife(unsigned int i_life){ lifetime = i_life;}
	int getLife(){ return lifetime; }

};
