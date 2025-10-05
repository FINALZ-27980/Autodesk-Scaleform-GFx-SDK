#include "GenUtils.h"

/*******************************************************************************************/
/*NamedObject                                                                              */
/*                                                                                         */
/*******************************************************************************************/

NamedObject::NamedObject(const char*  argName)
{
  if(argName)
    name =  argName;
}

NamedObject::NamedObject(const std::string &argName)
{
  name = argName;
}

NamedObject::NamedObject(const NamedObject &copy)
{
  if(this != &copy)
    name = copy.name;
}

NamedObject &NamedObject::operator=(const NamedObject &copy)
{
  if(this != &copy)
    name = copy.name;
  return *this;
}

void NamedObject::setName(const char   *nameArg)
{
  if(nameArg)
    name = nameArg;
  else
    name.clear();
}

void NamedObject::setName(const std::string &nameArg)
{
  name = nameArg;
}

const std::string &NamedObject::getName() const
{
  return name;
}

const char *NamedObject::getCharName() const
{
  return  name.c_str();
}

NamedObject::~NamedObject()
{
  name.clear();
}

/*******************************************************************************************/
/*Logger                                                                                   */
/*                                                                                         */
/*******************************************************************************************/

std::vector<std::string> Logger::logStrings;
std::string              Logger::logPath;

void Logger::initialize(const char* logfilename)
{
  logPath     = !logfilename ? "Log.txt" : logfilename;
  std::ofstream logFile(logPath.c_str());
  logFile.close();
}

void Logger::flush()
{
  if(!logPath.size() || !logStrings.size())
    return;

  std::ofstream logFile(logPath.c_str(), std::ios::app);

  for(size_t t = 0; t < logStrings.size(); t++)
    logFile << logStrings[t];

  logStrings.clear();
  logFile.close();
}

void Logger::writeImmidiateInfoLog(const std::string &info)
{
  if(info.size())
  {
    logStrings.push_back(std::string("<+>") + info + "\n");
    flush();
  }
}

void Logger::writeInfoLog(const std::string &info)
{
  logStrings.push_back(std::string("<+>") + info + "\n");
  if(logStrings.size() >= 10)
    flush();
}

bool Logger::writeErrorLog(const std::string &info)
{
  if(info.size())
  {
    logStrings.push_back(std::string("<!>") + info + "\n");
    flush();
  }
  return false;
}

void Logger::writeFatalErrorLog(const std::string &info)
{
  if(info.size())
  {
   logStrings.push_back(std::string("<X>") + info + "\n");

    flush();
  }
  exit(1);
}

/*******************************************************************************************/
/*MediaPathManager                                                                         */
/*                                                                                         */
/*******************************************************************************************/

std::vector<std::string> MediaPathManager::dataPaths;

const std::string MediaPathManager::lookUpMediaPath(const std::string  &path)
{
  std::ifstream test;
  std::string   pathBuffer = path;
  size_t        count      = dataPaths.size();

  test.open(path.c_str());

  if(test.is_open())
  {
    test.close();
    return pathBuffer;
  }

  for(size_t i = 0; i < count; i++)
  {
    pathBuffer  = dataPaths[i];
    pathBuffer += path;

    test.open(pathBuffer.c_str());
    if(test.is_open())
    {
      test.close();
      break;
    }
  }

  return pathBuffer;
}

bool MediaPathManager::registerPath(const TiXmlElement *mediaPathNode)

{
  if(mediaPathNode)
   return  registerPath(mediaPathNode->Attribute("path"));

  return false;
}

bool MediaPathManager::registerPath(const std::string  &path)
{
  if(!path.size())
    return Logger::writeErrorLog("Failed to register data path -> NULL");

  for(size_t i = 0; i < dataPaths.size(); i++)
    if(dataPaths[i] == path)
      return true;

  std::string stringBuffer = path;

  Logger::writeInfoLog(std::string("Registering data path -> ") + path);
  dataPaths.push_back(stringBuffer);
  return true;
}

int MediaPathManager::getPathCount()
{
  return int(dataPaths.size());
}

const std::string MediaPathManager::getPathAt(int index)
{
  if(!dataPaths.size() || index >= int(dataPaths.size()) || index < 0)
    return NULL;
  return dataPaths[size_t(index)];
}

void  MediaPathManager::printAllPaths()
{
  std::cout << "List of registred Media Paths: \n";

  for(size_t i = 0; i < dataPaths.size(); i++)
    std::cout << int(i) << "-" << dataPaths[i].c_str() << std::endl;

  std::cout << std::endl;
}

/*******************************************************************************************/
/*Perlin                                                                                   */
/*                                                                                         */
/*******************************************************************************************/

#include <sstream>

#define MAXB 0x100
#define N 0x1000
#define NP 12   // 2^N
#define NM 0xfff

#define s_curve(t) ( t * t * (3. - 2. * t) )
#define lerp(t, a, b) ( a + t * (b - a) )
#define setup(i, b0, b1, r0, r1)\
        t = vec[i] + N;\
        b0 = ((int)t) & BM;\
        b1 = (b0+1) & BM;\
        r0 = t - (int)t;\
        r1 = r0 - 1.;
#define at2(rx, ry) ( rx * q[0] + ry * q[1] )
#define at3(rx, ry, rz) ( rx * q[0] + ry * q[1] + rz * q[2] )

static int p[MAXB + MAXB + 2];
static double g3[MAXB + MAXB + 2][3];
static double g2[MAXB + MAXB + 2][2];
static double g1[MAXB + MAXB + 2];

int start = 1;
int B     = 4;
int BM    = 3;


int  Perlin::getNoiseFrequency()
{
  return B;
}

void Perlin::setNoiseFrequency(int frequency)
{
  start = 1;
  B     = frequency;
  BM    = B-1;
}

double Perlin::noise1(double arg)
{
	int bx0, bx1;
	double rx0, rx1, sx, t, u, v, vec[1];

	vec[0] = arg;
	if (start)
	{
		start = 0;
		initialize();
	}

	setup(0, bx0, bx1, rx0, rx1);

	sx = s_curve(rx0);
	u = rx0 * g1[p[bx0]];
	v = rx1 * g1[p[bx1]];

	return(lerp(sx, u, v));
}

double Perlin::noise2(double vec[2])
{
	int bx0, bx1, by0, by1, b00, b10, b01, b11;
	double rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
	int i, j;

	if (start)
	{
		start = 0;
		initialize();
	}

	setup(0, bx0, bx1, rx0, rx1);
	setup(1, by0, by1, ry0, ry1);

	i = p[bx0];
	j = p[bx1];

	b00 = p[i + by0];
	b10 = p[j + by0];
	b01 = p[i + by1];
	b11 = p[j + by1];

	sx = s_curve(rx0);
	sy = s_curve(ry0);

	q = g2[b00]; u = at2(rx0, ry0);
	q = g2[b10]; v = at2(rx1, ry0);
	a = lerp(sx, u, v);

	q = g2[b01]; u = at2(rx0, ry1);
	q = g2[b11]; v = at2(rx1, ry1);
	b = lerp(sx, u, v);

	return lerp(sy, a, b);
}

double Perlin::noise3(double vec[3])
{
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
	double rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
	int i, j;

	if (start)
	{
		start = 0;
		initialize();
	}

	setup(0, bx0, bx1, rx0, rx1);
	setup(1, by0, by1, ry0, ry1);
	setup(2, bz0, bz1, rz0, rz1);

	i = p[bx0];
	j = p[bx1];

	b00 = p[i + by0];
	b10 = p[j + by0];
	b01 = p[i + by1];
	b11 = p[j + by1];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);

	q = g3[b00 + bz0]; u = at3(rx0, ry0, rz0);
	q = g3[b10 + bz0]; v = at3(rx1, ry0, rz0);
	a = lerp(t, u, v);

	q = g3[b01 + bz0]; u = at3(rx0, ry1, rz0);
	q = g3[b11 + bz0]; v = at3(rx1, ry1, rz0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g3[b00 + bz1]; u = at3(rx0, ry0, rz1);
	q = g3[b10 + bz1]; v = at3(rx1, ry0, rz1);
	a = lerp(t, u, v);

	q = g3[b01 + bz1]; u = at3(rx0, ry1, rz1);
	q = g3[b11 + bz1]; v = at3(rx1, ry1, rz1);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);

	return lerp(sz, c, d);
}

void Perlin::normalize2(double v[2])
{
	double s;

	s = sqrt(v[0] * v[0] + v[1] * v[1]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
}

void Perlin::normalize3(double v[3])
{
   double s;

  s    = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  v[0] = v[0] / s;
  v[1] = v[1] / s;
  v[2] = v[2] / s;
}

void Perlin::initialize()
{
	int i, j, k;

	srand(30757);
	for (i = 0; i < B; i++)
	{
		p[i] = i;
		g1[i] = (double)((rand() % (B + B)) - B) / B;

		for (j = 0; j < 2; j++)
			g2[i][j] = (double)((rand() % (B + B)) - B) / B;
		normalize2(g2[i]);

		for (j = 0; j < 3; j++)
			g3[i][j] = (double)((rand() % (B + B)) - B) / B;
		normalize3(g3[i]);
	}

	while (--i)
	{
		k = p[i];
		p[i] = p[j = rand() % B];
		p[j] = k;
	}

	for (i = 0; i < B + 2; i++)
	{
		p[B + i] = p[i];
		g1[B + i] = g1[i];
		for (j = 0; j < 2; j++)
			g2[B + i][j] = g2[i][j];
		for (j = 0; j < 3; j++)
			g3[B + i][j] = g3[i][j];
	}
}

// My harmonic summing functions - PDB

//
// In what follows "alpha" is the weight when the sum is formed.
// Typically it is 2, As this approaches 1 the function is noisier.
// "beta" is the harmonic scaling/spacing, typically 2.
//

double Perlin::noise1D(double x,double alpha,double beta,int n)
{
	int i;
	double val,sum = 0;
	double p,scale = 1;

	p = x;
	for (i = 0; i < n; i++)
	{
		val = noise1(p);
		sum += val / scale;
		scale *= alpha;
		p *= beta;
	}
	return(sum);
}

double Perlin::noise2D(double x, double y, double alpha, double beta, int n)
{
	int i;
	double val, sum = 0;
	double p[2], scale = 1;

	p[0] = x;
	p[1] = y;
	for (i = 0; i < n; i++)
	{
		val = noise2(p);
		sum += val / scale;
		scale *= alpha;
		p[0] *= beta;
		p[1] *= beta;
	}
	return(sum);
	}

double Perlin::noise3D(double x, double y, double z, double alpha, double beta, int n)
{
  int i;
  double val,sum = 0;
  double p[3],scale = 1;

  p[0] = x;
  p[1] = y;
  p[2] = z;

  for (i = 0; i < n; i++)
  {
    val    = noise3(p);
    sum   += val / scale;
    scale *= alpha;
    p[0]  *= beta;
    p[1]  *= beta;
    p[2]  *= beta;
  }
  return(sum);
}


