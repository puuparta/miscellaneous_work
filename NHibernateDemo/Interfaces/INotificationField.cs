namespace Interfaces
{
    public interface INotificationField
    {
        int Id { get; set; }
        int NotificationId { get; set; }
        string Fieldname { get; set; }
    }
}