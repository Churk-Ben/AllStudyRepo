public class AccountTest {
    public static void main(String[] args) {
        BankAccount acc1 = new BankAccount("张正珂", 20248329, 0476, BankAccountGrade.VIP);
        acc1.setBalance(acc1.getBalance() + 100);
        System.out.println("Account: " + acc1);
        System.out.println("Account Name: " + acc1.getOwnerName());
        System.out.println("Account Number: " + acc1.getAccountNumber());
        System.out.println("Balance: $" + acc1.getBalance());
        System.out.println("Grade: " + acc1.getGrade());
    }
}
