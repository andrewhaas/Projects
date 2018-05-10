#include<string>
class unbounded
{
 public:
  unbounded(std::string value);
  unbounded();
  unbounded(const unbounded & other); 
  ~unbounded();
  const unbounded operator+ (const unbounded & rhs) const;
  const unbounded operator- (const unbounded & rhs) const;
  const unbounded operator/ (const unbounded & rhs) const;
  const unbounded operator* (const unbounded & rhs) const;
  const unbounded operator% (const unbounded & rhs) const;
  unbounded & operator= (const unbounded & rhs);

  std::string get_value()const;
 private:
  std::string value;
  

};
