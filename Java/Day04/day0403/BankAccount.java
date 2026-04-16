enum BankAccountGrade { // 定义枚举类型，表示账户的等级。共有两种等级：VIP和GENERAL
    VIP,
    General;
}

public class BankAccount {
    private String ownerName;
    private int accountNumber;
    private float balance;
    BankAccountGrade grade;

    public BankAccount() {
        this("", 0, 0, BankAccountGrade.General);
    }

    public BankAccount(String initName, int initAccNum, float initBal,
            BankAccountGrade g) {
        ownerName = initName;
        accountNumber = initAccNum;
        balance = initBal;
        grade = g;
    }

    public String getOwnerName() {
        return ownerName;
    }

    public int getAccountNumber() {
        return accountNumber;
    }

    public float getBalance() {
        return balance;
    }

    public BankAccountGrade getGrade() {
        return grade;
    }

    public void setOwnerName(String newName) {
        ownerName = newName;
    }

    public void setAccountNumber(int newNum) {
        accountNumber = newNum;
    }

    public void setBalance(float newBalance) {
        balance = newBalance;
    }

    public void setGrade(BankAccountGrade g) {
        grade = g;
    }
}
