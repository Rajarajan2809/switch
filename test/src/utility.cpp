#include "switch.h"

//function to remove specific char
String charRemove(String data,String ch)
{
	String res;
	for(int i=0; data.indexOf(ch); i++)
	{
		res += data.substring(0,data.indexOf(ch));
		res.remove(0,data.indexOf(ch)+1);
	}
	return res;
}
