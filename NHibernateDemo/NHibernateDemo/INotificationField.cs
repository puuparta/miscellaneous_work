using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Interfaces
{
    public interface INotificationField
    {
        int Id { get; set; }
        int NotificationId { get; set; }
        string Fieldname { get; set; }
    }
}
