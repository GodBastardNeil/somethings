#include "payment.h"

/*методы money*/
std::istream& operator>>(std::istream& t, payment::money &m)
{
    unsigned long long R;
    unsigned char C;
    t >> R >> C;
    m = payment::money(R, C);
    return t;
}

std::string payment::money::toString() noexcept {
    std::string s;
    s += std::to_string(r) + ",";
    if(c<10) { s += '0'; }
    s += std::to_string(c) + " руб.";
    return s;
}
std::ostream& operator<<(std::ostream& t, payment::money &m) noexcept { return (t << m.toString() << std::endl); }

payment::money& payment::money::operator+=(const money &b) noexcept
{
    double l = (to_cop() + b.to_cop());
    r = unsigned(l)/100;
    c = u_char(l - r*100);
    return *this;
}

payment::money& payment::money::operator-=(const money &b)
{
    double l = (to_cop() - b.to_cop());
    if (l<0) {
        throw less_then_0(); // исключение
    } else {
        r = unsigned(l)/100;
        c = u_char(l - r*100);
    }
    return *this;
}

payment::money &payment::money::operator*=(const double &b) noexcept
{
    u_long umnoch = u_long(to_cop()*b);
    r = umnoch/100;
    c = umnoch%100;
    return *this;
}

payment::money &payment::money::operator*=(const payment::money &b) noexcept
{
    double l = (to_cop() * b.to_cop());
    r = unsigned(l)/100;
    c = u_char(l - r*100);
    return *this;
}

payment::money operator-(const payment::money &a, const payment::money &b)
{
    payment::money tmp = a;
    tmp -= b;
    return tmp;
}

payment::money operator+(const payment::money &a, const payment::money &b) noexcept
{
    payment::money tmp = a;
    tmp += b;
    return tmp;
}

payment::money operator*(const payment::money &a, const double &b) noexcept
{
    payment::money tmp = a;
    tmp *= b;
    return tmp;
}
payment::money operator*(const payment::money &a, const payment::money &b) noexcept
{
    payment::money tmp = a;
    tmp *= b;
    return tmp;
}

double operator/(const payment::money &a, const payment::money &b) noexcept  { return a.to_cop()/b.to_cop(); }

double operator/(const payment::money &a, const double &b) noexcept { return a.to_cop()/(b); }


bool operator==(const payment::money &a, const payment::money &b) noexcept { return (a.r == b.r) && (a.c == b.c); }

bool operator!=(const payment::money &a, const payment::money &b) noexcept { return !(a == b); }

bool operator<(const payment::money &a, const payment::money &b) noexcept { return a.to_cop() < b.to_cop(); }

bool operator>(const payment::money &a, const payment::money &b) noexcept { return a.to_cop() > b.to_cop(); }

bool operator<=(const payment::money &a, const payment::money &b) noexcept { return !(a>b); }

bool operator>=(const payment::money &a, const payment::money &b) noexcept { return !(a<b); }
/*методы money*/

/*методы payment*/
std::string payment::toString() noexcept
{
    std::string s;
    s = "\nФамилия: " + name +
    "\nОклад: " + sum.toString() +
    "\nНадбавка: " + allowance.toString() +
    "\nНачислено: " + accrued_sum.toString() +
    "\nПенсионные отчисления: " + pension.toString() +
    "\nПодоходный налог: " + income_tax.toString() +
    "\nУдержано: " + witheld_sum.toString() +
    "\nСумма, выдаваемая на руки: " + final_sum.toString() +
    "\nКоличество рабочих дней: " + std::to_string(work_days) +
    "\nКоличество отработанных дней: " + std::to_string(days_developed);
    return s;
}


std::istream& operator>>(std::istream& t, payment &p)
{
    std::string n;
    payment::money s;
    double out_allowance;
    uint8_t out_work_days, out_days_developed;

        std::cout << "\nВведите фамилию: ";
        t >> n;
        std::cout << "\nВведите величину оклада: ";
        t >> s;
        do {
            std::cout << "\nПроцент надбавки: ";
            t >> out_allowance;
        } while (out_allowance < 0);
        std::cout << "\nВведите количество рабочих дней: ";
        t >> out_work_days;
        std::cout << "\nВведите количество отработанных дней: ";
        t >> out_days_developed;

    p = payment(n, out_allowance, out_work_days, out_days_developed, s);
    return t;
}

std::ostream& operator<<(std::ostream& t, payment &p) noexcept { return (t << p.toString() << std::endl); }

// Изменение оклада
void payment::set_sum(const money &s) { sum = s; init(); }
void payment::set_sum(unsigned long long R, unsigned char C) { sum = money{R, C}; init(); }

// Изменение надбавки
void payment::set_allowance(const double &new_allowance)
{
    if(new_allowance < 0) {
        throw "\nПроцент надбавки не может быть отрицательным";
    }
    percent = new_allowance/100;
    init();
}

// Расчёт надбавки
payment::money payment::finding_allowance() noexcept { return sum*(percent); }

// Расчёт начисленной суммы
payment::money payment::finding_accrued_sum() noexcept { return sum*(days_developed/work_days) + allowance; }

// Расчёт суммы пенсионных отчислений
payment::money payment::finding_pension() noexcept { return accrued_sum*(percent_of_pension); }

// Расчёт суммы подоходного налога
payment::money payment::finding_income_tax() noexcept { return ((accrued_sum - pension)*percent_of_income_tax); }

// Вычисление удержанной суммы
payment::money payment::finding_witheld_sum() noexcept { return income_tax + pension; }

// Вычисление суммы, выдаваемой на руки
payment::money payment::finding_final_sum() noexcept { return accrued_sum - witheld_sum; }


// сравнение по окладу
bool operator==(const payment &a, const payment &b) noexcept { return a.sum == b.sum; }

bool operator!=(const payment &a, const payment &b) noexcept { return !(a == b); }

bool operator<(const payment &a, const payment &b) noexcept { return a.sum < b.sum; }

bool operator>(const payment &a, const payment &b) noexcept { return a.sum > b.sum; }

bool operator<=(const payment &a, const payment &b) noexcept { return !(a>b); }

bool operator>=(const payment &a, const payment &b) noexcept { return !(a<b); }
/*методы payment*/

