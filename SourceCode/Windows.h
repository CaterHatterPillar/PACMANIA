#ifndef WINDOWSCONTAINER_H
#define WINDOWSCONTAINER_H

class Windows
{
private:
protected:
public:
	void main(
		HINSTANCE	hInstance, 
		HINSTANCE	hPrevInstance, 
		LPSTR		lpCmdLine, 
		int			nCmdShow);

	Windows()	{}
	~Windows()	{}
};

#endif //WINDOWSCONTAINER_H