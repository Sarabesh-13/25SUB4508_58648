: 'bash script for storing salary and calculating hra,da and gross salary'

read -p "enter your salary for calculating hra and da and gross salary:" salary
echo "your salary is $salary"

HRA=$((salary * 20/100))
DA=$((salary * 15/100))
echo "HRA = $HRA"
echo "DA = $DA"
echo "Gross Salary = $((salary+HRA+DA))"