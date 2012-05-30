
#include "../comm.h"

class MeasureModel
{
    protected:

    public:
      /// Constructor
      MeasureModel(Matrix h, Matrix r);
	  MeasureModel(const MeasureModel &m);

      /// Destructor
      virtual ~MeasureModel();
  
	  //更新模型
	  void UpdateModel(Matrix h, Matrix r);
	  
	  //设置量测转移矩阵
	  void SetH(Matrix h);
	  
	  //获得量测转移矩阵
	  Matrix GetH();

	  //设置量测噪声协方差
	  void SetR(Matrix r);
	  
	  //获得量测噪声协方差
	  Matrix GetR();

	  static MeasureModel getModel();

    private:
	  Matrix H;
	  Matrix R;

};
