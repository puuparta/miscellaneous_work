using System.Collections.Generic;

namespace Domain.Notification
{
    public class Notification : INotification
    {
        public Notification()
        {
            NotificationFields = new List<INotificationField>();
        }

        public virtual int Id { get; set; }
        public virtual string FirstName { get; set; }
        public virtual IList<INotificationField> NotificationFields { get; set; }
    }
}