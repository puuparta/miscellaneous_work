using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace Domain.Model.Kohde
{
    [Table("Kohde")]
    public class Kohde
    {
        [Key]
        public int Id { get; set; }

        [MaxLength(30,ErrorMessage="Too looong")]
        public string Osoite { get; set; }
    }
}
