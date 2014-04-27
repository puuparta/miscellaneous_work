using System.Collections.Generic;

namespace Interfaces
{
    public interface INotification
    {
        int Id { get; set; }
        string FirstName { get; set; }
        IList<INotificationField> NotificationFields { get; set; }
    }
}