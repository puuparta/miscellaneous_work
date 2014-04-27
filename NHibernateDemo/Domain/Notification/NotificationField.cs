namespace Domain.Notification
{
    public class NotificationField : INotificationField, IExtendedNotificationField
    {
        public virtual int GetExtendedAll()
        {
            return 42;
        }

        public virtual int Id { get; set; }
        public virtual int NotificationId { get; set; }
        public virtual string Fieldname { get; set; }
    }


    public interface IExtendedNotificationField
    {
        int GetExtendedAll();
    }
}