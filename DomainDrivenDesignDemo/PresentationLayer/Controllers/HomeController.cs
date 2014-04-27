using System.Web.Mvc;

namespace PresentationLayer.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            ViewBag.Message = "Blaa Blaa";

            return View();
        }
    }
}
